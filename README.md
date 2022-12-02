# HITman ShoppingLikeFiles NativeComponent

[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=BME-Crysys-HITMan_ShoppingLikeFiles-NativeComponent&metric=coverage)](https://sonarcloud.io/summary/new_code?id=BME-Crysys-HITMan_ShoppingLikeFiles-NativeComponent)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=BME-Crysys-HITMan_ShoppingLikeFiles-NativeComponent&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=BME-Crysys-HITMan_ShoppingLikeFiles-NativeComponent)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=BME-Crysys-HITMan_ShoppingLikeFiles-NativeComponent&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=BME-Crysys-HITMan_ShoppingLikeFiles-NativeComponent)

This repository contains all project and necessities for the native component part of the application

Documentation could be found [in this document](docs/README.md).

# Example runs

## Windows 

```shell
.\CAFF_Processor.exe "Z:\\BME\\MSc\\SzamBiz\\ShoppingLikeFlies.DomainServices\\test\\DomainServices.UnitTest\\bin\\Debug\\net6.0\\validfile.caff" --validate 
.\CAFF_Processor.exe "Z:\\BME\\MSc\\SzamBiz\\ShoppingLikeFlies.DomainServices\\test\\DomainServices.UnitTest\\bin\\Debug\\net6.0\\validfile.caff" --getThumbnail "Z:\\BME\\MSc\\SzamBiz\\ShoppingLikeFlies.DomainServices\\test\\DomainServices.UnitTest\\bin\\Debug\\net6.0\\generator"
```

## Linux

```bash
./CAFF_Processor ../afl/testfiles/1.caff --validate
./CAFF_Processor ../afl/testfiles/1.caff --getThumbnail ./generator
```