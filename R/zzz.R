##
## zzz: initialization of rimage
##
## $Header: /home/repository/rimage/R/zzz.R,v 1.1.2.4 2003/04/07 07:32:29 tomo Exp $
##
## Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
## For complete license terms see file LICENSE

.First.lib <- function(lib, pkg) {
  library.dynam("rimage", pkg, lib)
}


# the end of file
