# mod_solod

FreeSWITCH module implemented in https://github.com/solod-dev/solod/ .

It does NOTHING.

build with `so`

```
make
```

alternatively, build with C

```
make gen
make c
```

install:

```
make install
```

run in FreeSWITCH:

```
load mod_solod                # Load
solod                         # The API
originate null/1234 &solod    # The App
```
