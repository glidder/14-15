#!/bin/bash

simversion=$(./simulador/simulador -version)
utilversion=$(cat .version)
soversion=$(getconf LONG_BIT)

echo "Current simulator version: $simversion"
echo "Current utilities version: $utilversion"
echo "SO version: $soversion"

suffix=
if [ "$soversion" = "64" ]
then
    suffix=64
fi

if [ "$simversion" = "1.6" ]
then
    echo "Nothing to update"
elif [ "$simversion" = "1.5" ]
then
    echo "Updating to 1.6..."
    rm update.tar.gz*
    if [ "$soversion" = "64" ]
    then
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=18f0f3f30244d466e4bab7dffc9a0487\&download && echo a > .version
    else
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=039b397a957613c01deaadc6ccfe2da4\&download && echo a > .version
    fi
    tar -xzf update.tar.gz --directory ..
    rm update.tar.gz*
    echo "Updated to 1.6"
elif [ "$simversion" = "1.4" ]
then
    echo "Updating to 1.5..."
    rm update.tar.gz*
    if [ "$soversion" = "64" ]
    then
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=72cca89abdc6be355be44f7d51a2f3a2\&download && echo a > .version
    else
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=88e36879e93bbc729c6c9ba7951c234a\&download && echo a > .version
    fi
    tar -xzf update.tar.gz --directory ..
    rm update.tar.gz*
    echo "Updated to 1.5"
elif [ "$simversion" = "1.3" ]
then
    echo "Updating to 1.4..."
    rm update.tar.gz*
    if [ "$soversion" = "64" ]
    then
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=f4bae162bae5986585d7e95327dab901\&download && echo a > .version
    else
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=cedab42a8a722cea583633f2cd0fd4a9\&download && echo a > .version
    fi
    tar -xzf update.tar.gz --directory ..
    rm update.tar.gz*
    echo "Updated to 1.4"
elif [ "$simversion" = "1.2" ]
then
    echo "Updating to 1.4..."
    rm update.tar.gz*
    if [ "$soversion" = "64" ]
    then
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=f4bae162bae5986585d7e95327dab901\&download && echo a > .version
    else
        wget -O update.tar.gz https://nube.uca.es/public.php?service=files\&t=cedab42a8a722cea583633f2cd0fd4a9\&download && echo a > .version
    fi
    tar -xzf update.tar.gz --directory ..
    rm update.tar.gz*
    echo "Updated to 1.4"
else
    echo "Error: unknown version"
fi

