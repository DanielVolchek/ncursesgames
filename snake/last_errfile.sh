#!/bin/bash
inital_wd=`pwd`
goto_wd='/home/danielvolchek/ncursesgames/errfiles'
cd $goto_wd
ls -At | head -n 1 | xargs cat
cd $initial_wd
