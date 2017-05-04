#! /bin/sh
xl destroy click0
xl create config.xen
../../cosmos/dist/bin/cosmos start click0 ids.click
