#!/bin/sh
if [ -f Ultraschall-1.3beta2.dmg ]; then
	rm -f Ultraschall-1.3beta2.dmg
fi

if [ -f Ultraschall-1.3beta2.dmg.zip ]; then
	rm -f Ultraschall-1.3beta2.dmg.zip
fi

make-plugin-package.sh
make-soundboard-package.sh
make-sws-package.sh
make-resources-package.sh
make-soundfloweruninstaller-package.sh
make-ultraschall-package.sh

productsign --sign "Developer ID Installer: Heiko Panjas (8J2G689FCZ)" Payload/Ultraschall-unsigned.pkg Payload/Ultraschall-1.3beta2.pkg
rm Payload/Ultraschall-unsigned.pkg

hdiutil create -size 100m -srcfolder ./Payload -fs HFS+ -volname "Ultraschall 1.3beta2" ./Ultraschall-1.3beta2.dmg
zip Ultraschall-1.3beta2.dmg.zip Ultraschall-1.3beta2.dmg
rm Ultraschall-1.3beta2.dmg


