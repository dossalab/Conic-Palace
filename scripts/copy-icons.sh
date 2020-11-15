#!/usr/bin/env bash

#
# Sourced from
# https://github.com/jhekasoft/insteadman/blob/master/gtk-copy-icons.sh,
# which is under MIT license
#

input_path=$1
output_path=$2

if [[ -z "$input_path" || -z "$output_path" ]]; then
  echo "usage: $0 <input_path> <output_path>"
  exit 1
fi

icons=('window-close-symbolic.*' 'window-maximize-symbolic.*'
       'window-minimize-symbolic.*')

icons_dirs=('16x16' '32x32' '64x64')

# Copy icons
theme_output_path=$output_path'/share/icons/Adwaita'
theme_path=$input_path'/share/icons/Adwaita'
for icon_dir in "${icons_dirs[@]}"
do
    mkdir -p $theme_output_path'/'$icon_dir'/ui'

    for icon in "${icons[@]}"
    do
        cp $theme_path'/'$icon_dir'/ui/'$icon $theme_output_path'/'$icon_dir'/ui'
    done
done

# Copy spinner icon
loader_icon='process-working-symbolic.svg'
mkdir -p $theme_output_path'/scalable-up-to-32/status'
cp $theme_path'/scalable-up-to-32/status/'$loader_icon $theme_output_path'/scalable-up-to-32/status/'$loader_icon

# Copy theme file
theme_file='index.theme'
cp $theme_path'/'$theme_file $theme_output_path'/'$theme_file
