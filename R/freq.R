## $Header: /home/repository/rimage/R/freq.R,v 1.1.2.2 2003/04/07 07:32:29 tomo Exp $
##
## Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
## For complete license terms see file LICENSE


lowpass <- function(img, radius=40) {
  ## computes a low pass
  ## image is just for giving dimensions
  get.lp <- function(img, radius) {
    h <- dim(img)[1]
    w <- dim(img)[2]
    matrix(.C("getLowPass",
              as.double(img),
              as.integer(w),
              as.integer(h),
              as.integer(radius),
              spec = double(h*w)
              ##)$spec, nrow=dim(img)[1], ncol=dim(img)[2])
              )$spec, nrow=h, ncol=w)
  }
  fft <- fftw(img)
  t1 <- rbind(fft,fft)
  t2 <- cbind(t1,t1)
  x1 <- dim(fft)[1]/2 + 1
  x2 <- 1.5*dim(fft)[1]
  y1 <- dim(fft)[2]/2 + 1
  y2 <- 1.5*dim(fft)[2]
  fft <- t2[ x1:x2 , y1:y2 ]
  lp <- get.lp(img, radius)
  filtered <- fft*lp
  ifft <- fftw(filtered,1)
  imagematrix(abs(ifft), noclipping=TRUE)
}

highpass <- function(img, radius=40) {
  ## computes high pass
  get.hp <- function(img, radius) {
    h <- dim(img)[1]
    w <- dim(img)[2]
    matrix(.C("getHighPass",
              as.double(img),
              as.integer(w),
              as.integer(h),
              as.integer(radius),
              spec = double(w*h)
              )$spec, nrow=dim(img)[1], ncol=dim(img)[2])
  }
  fft <- fftw(img)
  t1 <- rbind(fft,fft)
  t2 <- cbind(t1,t1)
  x1 <- dim(fft)[1]/2 + 1
  x2 <- 1.5*dim(fft)[1]
  y1 <- dim(fft)[2]/2 + 1
  y2 <- 1.5*dim(fft)[2]
  fft <- t2[ x1:x2 , y1:y2 ]
  hp <- get.hp(img, radius)
  filtered <- fft*hp
  ifft <- fftw(filtered,1)
  imagematrix(abs(ifft), noclipping=TRUE)
}


## the end of file
