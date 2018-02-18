// NOTE: Incomplete, don't use

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class FRTreeElementId
{
public:
	template <typename, typename>
	friend class TRTree;

	FRTreeElementId()
		: Node(nullptr),
		ElementIndex(INDEX_NONE) { }

	bool IsValidId() const { return Node != nullptr; } 

private:
	const void* Node;
	int32 ElementIndex;

	FRTreeElementId(const void* InNode, int32 InElementIndex)
		: Node(InNode),
		ElementIndex(InElementIndex) { }

	operator int32() const { return ElementIndex; }
};

/* Example semantics */
/*
struct FExampleRTreeSemantics
{
	enum { MinElementsPerNode = 4 };
	enum { MaxElementsPerNode = 8 };

	typedef TInlineAllocator<MaxElementsPerNode> ElementAllocator;

	FORCEINLINE static const FVector& GetLocation(const AActor* InActor)
	{
		return InActor->GetActorLocation();
	}

	FORCEINLINE static bool AreElementsEqual(const AActor* InLeft, const AActor* InRight)
	{
		return InLeft == InRight;
	}

	static void SetElementId(const AActor* InElement, FRTreeElementId InId)
	{
		// TODO
	}
};
*/

// Based on https://github.com/Symphonym/Saurobyte/blob/master/src/Saurobyte/RTree.hpp
template <typename ElementType, typename RTreeSemantics>
class TRTree
{
public:
	typedef TArray<ElementType, typename RTreeSemantics::ElementAllocator> FElementArrayType;
	typedef typename FElementArrayType::TConstIterator FElementConstIterator;

	class FNode
	{
	public:
		friend class TRTree;

		explicit FNode(const FNode* InParent)
			: Parent(InParent),
			Level(InParent->Level + 1) 
		{
			Children.Reserve(RTreeSemantics::MinElementsPerNode);
		}

		FORCEINLINE FElementConstIterator GetElementIterator() const { return FElementConstIterator(Elements); }
		FORCEINLINE bool IsLeaf() { return Level == 0; }
		FORCEINLINE bool HasChildren() { return Children.Num() > 0; }
		FORCEINLINE FNode* GetChild(uint32 InIndex) const { return Children[InIndex]; }
		FORCEINLINE const FElementArrayType& GetElements() const { return Elements; }
		FORCEINLINE int32 GetElementCount() const { return Elements.Num(); }
		FORCEINLINE FBox& GetBounds() const { return Bounds; }

		void ShrinkElements()
		{
			Elements.Shrink();
			for (auto& Child : Children)
				if (Child != nullptr)
					Child->ShrinkElements();
		}

		void CalculateBounds()
		{
			float MinX = FLT_MAX;
			float MinY = FLT_MAX;
			float MinZ = FLT_MAX;

			float MaxX = FLT_MIN;
			float MaxY = FLT_MIN;
			float MinZ = FLT_MIN;

			for (size_t i = 0; i < Children.Num(); i++)
			{
				const FBox& Bounds = Children[i]->GetBounds();

				if (Bounds.Min.X < MinX)
					MinX = Bounds.Min.X;
				if (Bounds.Min.Y < MinY)
					MinY = Bounds.Min.Y;
				if (Bounds.Min.Z < MinZ)
					MinZ = Bounds.Min.Z;

				if (Bounds.Max.X > MaxX)
					MaxX = Bounds.Max.X;
				if (Bounds.Max.Y > MaxY)
					MaxY = Bounds.Max.Y;
				if (Bounds.Max.Z > MaxZ)
					MaxZ = Bounds.Max.Z;
			}

			this->Bounds = FBox(FVector(MinX, MinY, MinZ), FVector(MaxX, MaxY, MaxZ));
		}

		float CalculateOverlap(const FVector InPoint)
		{
			float Result = 0.0f;
			for (auto i = 0; i < Children.Num(); i++)
			{
				const FBox& Bounds = Children[i]->GetBounds();
				Result += CalculateOverlap(InPoint, Bounds);
			}
			return Result;
		}

		FNode* Split()
		{
			TArray<FNode*> SortedX = Children;
			TArray<FNode*> SortedY = Children;
			TArray<FNode*> SortedZ = Children;

			TArray<FNode*> SortedList = Children;
			uint32 OptimalDistributionK = 0;

			CalculateOptimalSplit(SortedList, OptimalDistributionK);
			OptimalDistributionK = (RTreeSemantics::MinElementsPerNode - 1) + OptimalDistributionK;

			Children.Empty();
			Children.Init(OptimalDistributionK);

			for (auto i = 0; i < OptimalDistributionK; i++)
				Children.Add(SortedList[i]);

			CalculateBounds();

			FNode* NewNode = new FNode();
			NewNode->Level = Level;

			for (auto i = OptimalDistributionK; i < RTreeSemantics::MaxElementsPerNode + 1; i++)
				NewNode->Children.Add(SortedList[i]);

			NewNode->CalculateBounds();

			return NewNode;
		}

	private:
		mutable FElementArrayType Elements;
		const FNode* Parent;
		mutable TArray<FNode*> Children;
		mutable uint32 Level;
		FBox Bounds;

		float GetPerimeter(const FBox& InBox)
		{
			FVector Size = InBox.GetSize();
			return 4.0f * (Size.X + Size.Y + Size.Z);
		}

		float CalculateOverlap(const FVector InPoint, const FBox& InBounds)
		{
			if (InBounds.IsInsideOrOn(InPoint))
			{
				float Width = FMath::Min(InBounds.Max.X, InPoint.X) - FMath::Max(InBounds.Min.X, InPoint.X);
				float Height = FMath::Min(InBounds.Max.Y, InPoint.Y) - FMath::Max(InBounds.Min.Y, InPoint.Y);
				float Depth = FMath::Min(InBounds.Max.Z, InPoint.Z) - FMath::Max(InBounds.Min.Z, InPoint.Z);
				return Width * Height * Depth;
			}

			return 0.0f;
		}

		float CalculateOverlap(const FBox& InBoxLeft, const FBox& InBoxRight)
		{
			if (InBoxLeft.Intersect(InBoxRight))
			{
				float Width = FMath::Min(InBoxRight.Max.X, InBoxLeft.Max.X) - FMath::Max(InBoxRight.Min.X, InBoxLeft.Min.X);
				float Height = FMath::Min(InBoxRight.Max.Y, InBoxLeft.Max.Y) - FMath::Max(InBoxRight.Min.Y, InBoxLeft.Min.Y);
				float Depth = FMath::Min(InBoxRight.Max.Z, InBoxLeft.Max.Z) - FMath::Max(InBoxRight.Min.Z, InBoxLeft.Min.Z);
				return Width * Height * Depth;
			}

			return 0.0f;
		}

		float CalculateOptimalSplit(TArray<FNode*>& InOutSortedAxisList, uint32& OutOptimalDistributionK)
		{
			uint32 SplitDistributions = RTreeSemantics::MaxElementsPerNode - (2 * RTreeSemantics::MinElementsPerNode) + 2;
			int32 SplitSort = 0, SplitAxis = 0, SplitK = 1;

			float LowestMargin = FLT_MAX;
			for (auto Axis = 0; Axis < 3; Axis++)
			{
				float MarginValue = 0.0f;
				float LowestOverlap = FLT_MAX;
				float LowestVolume = FLT_MAX;
				int32 BestK = 0;
				for (auto Sorting = 0; Sorting < 2; Sorting++)
				{
					Algo::Sort(InOutSortedAxisList, [&](const FNode* InLeft, const FNode* InRight) -> bool {
						if (Sorting == 0)
							return InLeft->GetBounds().Min[Axis] < InRight->GetBounds().Min[Axis];
						else
							return InLeft->GetBounds().Max[Axis] < InRight->GetBounds().Max[Axis];
					});

					for (auto k = 1; k < SplitDistributions; k++)
					{
						uint32 FirstElements = (RTreeSemantics::MinElementsPerNode - 1) + k;

						FBox FirstMinimumBounds = InOutSortedAxisList[0]->GetBounds();
						FBox SecondMinimumBounds = InOutSortedAxisList[FirstElements]->GetBounds();

						for (auto i = 1; i < FirstElements; i++)
							FirstMinimumBounds = UGameBaseFunctionLibrary::Encompass(FirstMinimumBounds, InOutSortedAxisList[FirstElements]->GetBounds());
							
						for (auto i = FirstElements + 1; i < RTreeSemantics::MaxElementsPerNode + 1; i++)
							SecondMinimumBounds = UGameBaseFunctionLibrary::Encompass(SecondMinimumBounds, InOutSortedAxisList[i]->GetBounds());

						MarginValue += GetPerimeter(FirstMinimumBounds) + GetPerimeter(SecondMinimumBounds);

						float OverlapValue = CalculateOverlap(FirstMinimumBounds, SecondMinimumBounds);
						float VolumeValue = FirstMinimumBounds.GetVolume() + SecondMinimumBounds.GetVolume();

						if (OverlapValue < LowestOverlap || (OverlapValue == LowestOverlap && VolumeValue < LowestVolume))
						{
							SplitSort = Sorting;
							LowestOverlap = OverlapValue;
							LowestVolume = VolumeValue;
							BestK = k;
						}
					}
					
					if (MarginValue < LowestMargin)
					{
						SplitAxis = Axis;
						SplitK = BestK;
						LowestMargin = MarginValue;
					}
				}
			}

			OutOptimalDistributionK = SplitK;
			Algo::Sort(InOutSortedAxisList, [&](const FNode* InLeft, const FNode* InRight) -> bool {
				if (SplitSort == 0)
					return InLeft->GetBounds().Min[SplitAxis] < InRight->GetBounds().Min[SplitAxis];
				else
					return InLeft->GetBounds().Max[SplitAxis] < InRight->GetBounds().Max[SplitAxis];
			});
		}
	};

	void AddElement(typename TTypeTraits<ElementType>::ConstInitType InElement);
	bool RemoveElement(FRTreeElementId InElementId);
	ElementType& GetElementById(FRTreeElementId InElementId);
	const ElementType& GetElementById(FRTreeElementId InElementId) const;
	bool IsValidElementId(FRTreeElementId InElementId) const;

	void Destroy()
	{
		
	}

	void ShrinkElements() { RootNode.ShrinkElements(); }

private:
	typedef TMap<uint32> FOverflowMap;
	typedef TArray<TPair<FNode*, FNode*>> FNodeSearchPath;

	FNode RootNode;
	const int32 ReinsertionFactor = RTreeSemantics::MaxElementsPerNode * 0.3;
	
	void AddElement(typename TTypeTraits<ElementType>::ConstInitType InElement, int32 InDesiredLevel, FOverflowMap& InOutOverflowMap);
	void FindNodeForElement(const FVector& InNewLocation, FNodeSearchPath& InOutSearchPath);
	void HandleOverflow(int32 InPathIndex, const FNodeSearchPath& InSearchPath, FOverflowMap& InOutOverflowMap);
	void Reinsert(FNode* InNode, FOverflowMap& InOverflowMap);
	bool Remove(FRTreeElementId InElementId, const FVector& InLocation, FNodeSearchPath& InOutSearchPath);
	void HandleUnderflow(int32 InPathIndex, const FNodeSearchPath& InSearchPath, FChildReinsertQueue& InOutNodesToReinsert);
	void HandleUnderflow(int32 InPathIndex, const FNodeSearchPath& InSearchPath);
};

template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::AddElement(typename TTypeTraits<ElementType>::ConstInitType InElement)
{
	FOverflowMap OverflowMap;
	AddElement(InElement, 0, OverflowMap);
}

template <typename ElementType, typename RTreeSemantics>
bool TRTree<ElementType, RTreeSemantics>::RemoveElement(FRTreeElementId InElementId)
{
	FNodeSearchPath SearchPath;
	SearchPath.Add(MakePair(RootNode, nullptr));
	bool bRemoved = Remove(InElementId, RTreeSemantics::GetLocation(/* TODO */), SearchPath);
	return bRemoved;
}

template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::AddElement(typename TTypeTraits<ElementType>::ConstInitType InElement, int32 InDesiredlevel, FOverflowMap& InOutOverflowMap)
{
	FNodeSearchPath SearchPath = FindNodeForElement(InElement);

	auto PathIndex = SearchPath.Num() - 1;
	while (SearchPath[PathIndex].Key->Level < InDesiredlevel)
		--PathIndex;

	FNode* Node = SearchPath[PathIndex].Key;
	FNode* Parent = SearchPath[PathIndex].Value;

	Node->Children.Add(InElement);
	Node->CalculateBounds();

	if (Node->Children.Num() > RTreeSemantics::MaxElementsPerNode)
		HandleOverflow(PathIndex, SearchPath, InOutOverflowMap);

	while (PathIndex <= 0)
	{
		FNode* NodeInPath = SearchPath[PathIndex].Key;
		NodeInPath->CalculateBounds();

		--PathIndex;
	}
}

template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::FindNodeForElement(const FVector& InNewLocation, FNodeSearchPath& InOutSearchPath)
{
	FNode& CurrentNode = *InOutSearchPath.Last().Key;
	if (CurrentNode.IsLeaf())
		return;
	else
	{
		if (CurrentNode.Level == 1)
		{
			TPair<float, int32> LowestOverlapNode = MakePair(FLT_MAX, 0);
			for (auto i = 0; i < CurrentNode.Children.Num(); i++)
			{
				FNode* Child = CurrentNode.GetChild(i);
				FBox ChildBounds = Child->GetBounds();
				float OverlapValue = Node->CalculateOverlap(InNewLocation);

				if (OverlapValue < LowestOverlapNode.Key)
					LowestOverlapNode = MakePair(OverlapValue, i);
				else if (OverlapValue == LowestOverlapNode.Key)
				{
					FBox CurrentMinimumBounds = CurrentNode.Children[LowestOverlapNode.Value]->GetBounds();
					float CurrentMinimumBoundsVolume = CurrentMinimumBounds.GetVolume();
					float CurrentMinimumBoundsDelta = UGameBaseFunctionLibrary::Encompass(CurrentMinimumBounds, InNewLocation).GetVolume() - CurrentMinimumBoundsVolume;

					float NewMimimumBoundsVolume = ChildBounds.GetVolume();
					float NewMimimumBoundsDelta = UGameBaseFunctionLibrary::Encompass(ChildBounds, InNewLocation).GetVolume() - NewMimimumBoundsVolume;

					if (NewMimimumBoundsDelta < CurrentMinimumBoundsDelta)
						LowestOverlapNode = MakePair(OverlapValue, i);
				}

				InOutSearchPath.Add(MakePair(CurrentNode.GetChild(LowestOverlapNode.Value), &CurrentNode));
				return FindNodeForElement(InNewLocation, InOutSearchPath);
			}
		}
	}
	else
	{
		TPair<float, int32> LowestMinimumBoundsNode = MakePair(FLT_MAX, 0);
		for (auto i = 0; i < CurrentNode.Children.Num(); i++)
		{
			FNode* Child = CurrentNode.GetChild(i);
			FBox ChildBounds = Child->GetBounds();

			FBox BiggerMinimumBounds = ChildBounds;
			BiggerMinimumBounds = UGameBaseFunctionLibrary::Encompass(BiggerMinimumBounds, InNewLocation);
			
			float NewMinimumBoundsDelta = BiggerMinimumBounds.GetVolume() - ChildBounds.GetVolume();

			if (NewMinimumBoundsDelta < LowestMinimumBoundsNode.Key)
				LowestMinimumBoundsNode = MakePair(NewMinimumBoundsDelta, i);
			else if (NewMinimumBoundsDelta == LowestMinimumBoundsNode.Key)
			{
				float CurrentVolume = CurrentNode.GetChild(LowestMinimumBoundsNode.Value)->GetBounds().GetVolume();
				float NewVolume = ChildBounds.GetVolume();

				if (NewVolume < CurrentVolume)
					LowestMinimumBoundsNode = MakePair(NewMinimumBoundsDelta, i);
			}
		}

		InOutSearchPath.Add(MakePair(CurrentNode.GetChild(LowestMinimumBoundsNode.Value), &CurrentNode));
		return FindNodeForElement(InNewLocation, InOutSearchPath);
	}
}

template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::HandleOverflow(int32 InPathIndex, const FNodeSearchPath& InSearchPath, FOverflowMap& InOutOverflowMap)
{
	FNode* OverflowNode = InSearchPath[InPathIndex].Key;
	FNode* Parent = InSearchPath[InPathIndex].Value;

	if (OverflowNode->Children.Num() > RTreeSemantics::MaxElementsPerNode)
	{
		if (OverflowNode->Level != RootNode->Level && InOutOverflowMap.Find(OverflowNode->Level) == InOutOverflowMap.Num() - 1)
		{
			InOutOverflowMap.Add(OverflowNode->Level);
			Reinsert(OverflowNode, InOutOverflowMap);
		}
		else
		{
			FNode* NewSplitNode = OverflowNode->Split();
			if (OverflowNode->Level == RootNode->Level)
			{
				FNode* NewRoot = new FNode();
				NewRoot->Children.Add(NewSplitNode);
				NewRoot->Children.Add(RootNode);
				NewRoot->CalculateBounds();
				NewRoot->Level = OverflowNode->Level + 1;
				Root = NewRoot;
			}
			else
			{
				Parent->Children.Add(NewSplitNode);
				Parent->CalculateBounds();
			}

			if (InPathIndex - 1 >= 0)
				HandleOverflow(InPathIndex - 1, InSearchPath, InOutOverflowMap);
		}
	}
}

template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::Reinsert(FNode* InNode, FOverflowMap& InOverflowMap)
{
	typedef TPair<float, FNode*> FDistanceChildPair;

	check(InNode->Children.Num() == RTreeSemantics::MaxElementsPerNode + 1);

	TArray<FDistanceChildPair> SortedByDistance;
	SortedByDistance.Reserve(RTreeSemantics::MaxElementsPerNode + 1);

	FVector NodeCenter = InNode->GetBounds().GetCenter();
	for (auto i = 0; i < InNode->Children.Num(); i++)
	{
		FVector ElementLocation = RTreeSemantics::GetLocation(InNode->GetChild(i));
		SortedByDistance.Add(MakePair(FVector::Distance(ElementLocation, NodeCenter), InNode->GetChild(i));
	}

	Algo::Sort(SortedByDistance, [](const FDistanceChildPair& InLeft, const FDistanceChildPair& InRight) -> bool
	{
		return InLeft.Key < InRight.Key;
	});

	int32 Start = SortedByDistance.Num() - 1 - ReinsertionFactor;
	int32 End = SortedByDistance.Num() - 1;

	TArray<FDistanceChildPair> ToRemove = UGameBaseFunctionLibrary::Splice(SortedByDistance, Start, End);
	SortedByDistance.RemoveAt(Start, End - Start);

	InNode->Children.Empty();
	InNode->Children.Reserve(SortedByDistance.Num());
	for (auto i = 0; i < SortedByDistance.Num(); i++)
		InNode->Children.Add(SortedByDistance[i].Value);

	InNode->CalculateBounds();

	for (auto i = 0; i < ToRemove.Num(); i++)
	{
		if (InNode->IsLeaf())
			Insert(ToRemove[i].Value, 0, InOverflowMap);
		else
			Insert(ToRemove[i].Value, InNode->Level, InOverflowMap);
	}
}

template <typename ElementType, typename RTreeSemantics>
bool TRTree<ElementType, RTreeSemantics>::Remove(FRTreeElementId InElementId, const FVector& InLocation, FNodeSearchPath& InOutSearchPath)
{
	FNode* Node = InOutSearchPath[0];
	for (auto i = 0; i < Node->Children.Num(); i++)
	{
		FNode* Child = Node->Children[i];
		if (Child->GetBounds().IsInsideOrOn(InLocation))
		{
			if (Node->IsLeaf())
			{
				if (InElementId == ? ? )
				{
					Node->Children.RemoveAt(i);
					
					delete Child;
					Child = nullptr;

					Node->CalculateBounds();

					HandleUnderflow(InOutSearchPath.Num() - 1, InOutSearchPath);

					return true;
				}
				else
				{
					InOutSearchPath.Add(MakePair(Child, Node));
					bool bRecursiveReturn = Remove(InElementId, InLocation, InOutSearchPath);

					if (bRecursiveReturn)
						return true;
				}
			}
		}
	}

	return false;
}

template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::HandleUnderflow(int32 InPathIndex, const FNodeSearchPath& InSearchPath, FChildReinsertQueue& InOutNodesToReinsert)
{
	FNode* UnderflowNode = InSearchPath[InPathIndex].Key;
	FNode* Parent = InSearchPath[InPathIndex].Value;

	if (UnderflowNode->Level == RootNode->Level)
	{
		if (!UnderflowNode->IsLeaf() && UnderflowNode->Children.Num() == 1)
		{
			RootNode = UnderflowNode->GetChild(0);
			RootNode->Level = UnderflowNode->Level - 1;

			delete UnderflowNode;
			UnderflowNode = nullptr;
		}

		RootNode->CalculateBounds();

		return;
	}

	if (UnderflowNode->Children.Num() < RTreeSemantics::MinElementsPerNode)
	{
		for (auto i = 0; i < UnderflowNode->Children.Num(); i++)
			InOutNodesToReinsert.Add(MakePair(UnderflowNode->GetChild(i), UnderflowNode->Level));

		UnderflowNode->Children.Empty();

		for (auto i = 0; i < Parent->Children.Num(); i++)
		{
			if (Parent->Children[i] == UnderflowNode)
			{
				delete Parent->Children[i];
				Parent->Children.RemoveAt(i);

				Parent->CalculateBounds();
				break;
			}
		}
	}

	HandleUnderflow(InPathIndex - 1, InSearchPath, InOutNodesToReinsert);
}


template <typename ElementType, typename RTreeSemantics>
void TRTree<ElementType, RTreeSemantics>::HandleUnderflow(int32 InPathIndex, FNodeSearchPath& InSearchPath)
{
	FChildReinsertQueue NodesToReinsert;
	HandleUnderflow(InPathIndex, InSearchPath, NodesToReinsert);

	for (auto i = 0; i < NodesToReinsert.Num(); i++)
	{
		FOverflowMap OverflowMap;
		Insert(NodesToReinsert[i].Key, NodesToReinsert[i].Value, OverflowMap);
	}
}