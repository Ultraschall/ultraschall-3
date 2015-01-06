#!/bin/sh
if [ -f Ultraschall-1.2.2.dmg ]; then
	rm -f Ultraschall-1.2.2.dmg
fi

if [ -f Ultraschall-1.2.2.dmg.zip ]; then
	rm -f Ultraschall-1.2.2.dmg.zip
fi

make-plugin-package.sh
make-soundboard-package.sh
make-sws-package.sh
make-resources-package.sh
make-soundfloweruninstaller-package.sh
make-ultraschall-package.sh

productsign --sign "Developer ID Installer: Heiko Panjas (8J2G689FCZ)" Payload/Ultraschall-1.2.2-unsigned.pkg Payload/Ultraschall-1.2.2.pkg
rm Payload/Ultraschall-1.2.2-unsigned.pkg

hdiutil create -size 50m -srcfolder ./Payload -fs HFS+ -volname "Ultraschall 1.2.2" ./Ultraschall-1.2.2.dmg
zip Ultraschall-1.2.2.dmg.zip Ultraschall-1.2.2.dmg
rm Ultraschall-1.2.2.dmg


