#!/bin/sh
if [ -f ./Build/UltraschallHub-1.2.dmg ]; then
	rm -f ./Build/UltraschallHub-1.2.dmg
fi

make-plugin-package.sh
make-soundboard-package.sh
make-sws-package.sh

make-ultraschall-package.sh

hdiutil create -size 50m -srcfolder ./Payload -fs HFS+ -volname UltraschallHub-1.2 ./UltraschallHub-1.2.dmg

