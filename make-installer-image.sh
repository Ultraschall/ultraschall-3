#!/bin/sh
if [ -f UltraschallHub-1.2_rc5.dmg.gz ]; then
	rm -f UltraschallHub-1.2_rc5.dmg.gz
fi

make-plugin-package.sh
make-soundboard-package.sh
make-sws-package.sh
make-resources-package.sh
make-soundfloweruninstaller-package.sh
make-ultraschall-package.sh

hdiutil create -size 50m -srcfolder ./Payload -fs HFS+ -volname UltraschallHub-1.2_RELEASE_CANDIDATE_5 ./UltraschallHub-1.2_rc5.dmg
gzip ./UltraschallHub-1.2_rc5.dmg

