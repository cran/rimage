##
## JPEG read functions
##
##  $Header: /home/repository/rimage/R/Attic/jpeg.R,v 1.1.2.2 2003/04/08 04:07:14 tomo Exp $
##
## Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
## For complete license terms see file LICENSE

read.jpeg <- function(filename) {
  res <- .C("get_imagesize_of_JPEG_file", as.character(filename),
            width=integer(1), height=integer(1), depth=integer(1),
            ret=integer(1))
  if (res$ret < 0)
    stop(if (res$ret==-1) "Can't open file." else "Internal error")
  imgtype <- if (res$depth == 1) "grey" else "rgb"
  imgdim <- c(res$height, res$width, if (res$depth == 3) res$depth else NULL)
  res <- .C("read_JPEG_file", as.character(filename),
            image=double(res$width * res$height * res$depth),
            ret=integer(1))
  img <- array(res$image, dim=imgdim)
  imagematrix(img/255, type=imgtype)
}

## the end of file

