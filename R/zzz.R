##
## zzz: initialization of rimage
##
## $Header: /database/repository/rimage/R/zzz.R,v 1.1.2.5 2004/03/17 06:35:18 tomo Exp $
##
## Copyright (c) 2003 Nikon Systems Inc.
## For complete license terms see file LICENSE

.First.lib <- function(lib, pkg) {
  library.dynam("rimage", pkg, lib)
}


# the end of file
