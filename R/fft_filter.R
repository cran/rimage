##
## fft_filter: fftw interface
##
## $Header: /home/repository/rimage/R/fft_filter.R,v 1.4.2.4 2003/04/07 07:32:29 tomo Exp $
##
## Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
## For complete license terms see file LICENSE

fftw <- function(img, dir = -1, debug=FALSE) {
  h <- dim(img)[1]
  w <- dim(img)[2]
  matrix(.C("fftw_access_func",
            as.complex(img),
            as.integer(w),
            as.integer(h),
            as.integer(dir),
            as.integer(debug),
            spec = complex(w*h)
            )$spec, nrow=dim(img)[1], ncol=dim(img)[2])
}

fftImg <- function(img) {
  img.fft <- normalize(imagematrix(log1p(Mod(fftw(img, -1))), noclipping=TRUE))
  # reordering
  w <- dim(img)[2]
  h <- dim(img)[1]
  imagematrix(img.fft[c(ceiling(h/2):h,1:(ceiling(h/2)-1)),
                      c(ceiling(w/2):w, 1:(ceiling(w/2)-1))], noclipping=TRUE)
}

## the end of file

