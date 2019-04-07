import unreal

def get_selected_assets():
    return unreal.EditorAssetLibrary2.get_selected()

def find_replace(assets, find_str, replace_str):
    for asset in assets:
        current_name = asset.get_name()
        new_name = current_name.replace(find_str, replace_str)
        unreal.EditorAssetLibrary2.rename(asset, new_name)

find = 'SM_'
replace = ''
selected_assets = get_selected_assets()
find_replace(selected_assets, find, replace)