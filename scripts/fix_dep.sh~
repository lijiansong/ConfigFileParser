#!/bin/bash

# Copyright (c) 2011 The Tupler Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file. See the AUTHORS file for names of contributors.
#
# Author: Hector Gonzalez (hagonzal@gmail.com)
#
# Fixes dependencies on a .d file
# Example:
#
# input dir/in.d:
# in.o : dir/b.cc dir/b.h dir2/d.h
#
# ./dev_scripts/fix_dep.sh dir/in.d
#
# output dir/in.d:
# dir/in.o: dir/b.cc dir/b.h dir2/d.h
# dir/b.cc:
# dir/b.h:
# dir2/d.h

if [ $# -ne 1 ]
then
  echo "Usage: fix_dep.sh file"
  exit 1
fi

file=`echo $1 | sed -e "s/\.d$//"`

mv $file.d $file.d.tmp
sed -e "s|.*:|$file.o:|" < $file.d.tmp > $file.d
sed -e 's/.*://' -e 's/\\$//' < $file.d.tmp | fmt -1 | \
sed -e 's/^ *//' -e 's/$/:/' >> $file.d
rm $file.d.tmp
