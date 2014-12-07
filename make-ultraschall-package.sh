#!/bin/sh
productbuild --distribution ./Scripts/distribution.xml --resources ./Resources --package-path ./Build ./Payload/UltraschallHub-1.2.pkg

productbuild --distribution ./Scripts/distribution_driver.xml --resources ./Resources --package-path ./Modules/Driver ./Payload/UltraschallDriver-1.2.pkg
