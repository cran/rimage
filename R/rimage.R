##
## rimage: Image Processing Library for R
##
## $Header: /home/repository/rimage/R/rimage.R,v 1.8.2.7 2003/04/08 02:59:57 tomo Exp $
##
## Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
## For complete license terms see file LICENSE


##
## Grey level adjustment
##

thresholding <- function(img, mode="fixed", th=0.5) {
  th.by.discrim <- function(img, L=255) {
    img.int <- floor(L*img)
    h <- hist(img.int, breaks=0:(L+1), plot=FALSE)$density
    lv <- 0:L
    u.img <- sum(lv * h) / sum(h)
    s.img <- sum(h * (lv - u.img)^2)
    Fs <- sapply(1:(L-1), function(k) {
      w.0 <- sum(h[1:k])
      w.1 <- sum(h[(k+1):L])
      u.0 <- sum((1:k) * h[1:k]) / w.0
      u.1 <- sum(((k+1):L) * h[(k+1):L]) / w.1
      s.B <- w.0 * (u.0 - u.img)^2 + w.1 * (u.1 - u.img)^2
      s.B / s.img
    })
    lv[rev(order(Fs, na.last = NA))[1]]/L
  }

  th <- switch(mode, fixed=th, da=th.by.discrim(img))
  if (is.null(th)) stop("Either mode or threshold isn't correct.")
  img[img < th] <- 0
  img[img >= th] <- 1
  img
}

clipping <- function(img, low=0, high=1) {
  img[img < low] <- low
  img[img > high] <- high
  img
}

normalize <- function(img) {
  (img - min(img))/(max(img) - min(img))
}

rgb2grey <- function(img, coefs=c(0.30, 0.59, 0.11)) {
  if (is.null(dim(img))) stop("image matrix isn't correct.")
  if (length(dim(img))<3) stop("image matrix isn't rgb image.")
  imagematrix(coefs[1] * img[,,1] + coefs[2] * img[,,2] + coefs[3] * img[,,3],
              type="grey")
}

##
## Edge Detection Filters
##

sobel.h <- function(img) {
  w <- dim(img)[2]
  h <- dim(img)[1]
  imagematrix(abs(matrix(.C("sobel_h",
                            as.double(img), as.integer(w), as.integer(h),
                            eimg = double(w * h))$eimg,
                         nrow=h, ncol=w)), noclipping=TRUE)
}

sobel.v <- function(img) {
  w <- dim(img)[2]
  h <- dim(img)[1]
  imagematrix(abs(matrix(.C("sobel_v",
                            as.double(img), as.integer(w), as.integer(h),
                            eimg = double(w * h))$eimg,
                         nrow=h, ncol=w)), noclipping=TRUE)
}

sobel <- function(img) {
  h.img <- sobel.h(img)
  v.img <- sobel.v(img)
  (h.img + v.img)/2
}

laplacian <- function(img) {
  w <- dim(img)[2]
  h <- dim(img)[1]
  l.img <- imagematrix(matrix(.C("laplacian",
                                 as.double(img), as.integer(w), as.integer(h),
                                 eimg = double(w * h))$eimg,
                              nrow=h, ncol=w),
                       noclipping=TRUE)
}

##
## Rank Filters
##

meanImg <- function(img) {
  expand.h <- cbind(img[,1], img, img[,dim(img)[2]])
  ex.img <- rbind(expand.h[1,], expand.h, expand.h[dim(img)[1],])
  w <- dim(ex.img)[2]
  h <- dim(ex.img)[1]
  f.img <- matrix(.C("meanfilter",
                     as.double(ex.img), as.integer(w), as.integer(h),
                     eimg = double(w * h))$eimg,
                  nrow=h, ncol=w)
  imagematrix(f.img[2:(dim(f.img)[1]-1),2:(dim(f.img)[2]-1)])
}

minImg <- function(img) {
  expand.h <- cbind(img[,1], img, img[,dim(img)[2]])
  ex.img <- rbind(expand.h[1,], expand.h, expand.h[dim(img)[1],])
  w <- dim(ex.img)[2]
  h <- dim(ex.img)[1]
  f.img <- matrix(.C("minfilter",
                     as.double(ex.img), as.integer(w), as.integer(h),
                     eimg = double(w * h))$eimg,
                  nrow=h, ncol=w)
  imagematrix(f.img[2:(dim(f.img)[1]-1),2:(dim(f.img)[2]-1)])
}

maxImg <- function(img) {
  expand.h <- cbind(img[,1], img, img[,dim(img)[2]])
  ex.img <- rbind(expand.h[1,], expand.h, expand.h[dim(img)[1],])
  w <- dim(ex.img)[2]
  h <- dim(ex.img)[1]
  f.img <- matrix(.C("maxfilter",
                     as.double(ex.img), as.integer(w), as.integer(h),
                     eimg = double(w * h))$eimg,
                  nrow=h, ncol=w)
  imagematrix(f.img[2:(dim(f.img)[1]-1),2:(dim(f.img)[2]-1)])
}


##
## Equalization
##


## image takes up values 0..1
equalize <- function(img) {
  img <- (img-min(img))*255 / (max(img)-min(img)) ## normalize it to 0..255
  h <- dim(img)[1]
  w <- dim(img)[2]
  res <- matrix(.C("equalize",
                   as.double(img),
                   as.integer(w),
                   as.integer(h),
                   spec = double(w*h)
                   )$spec, nrow=h, ncol=w)
  imagematrix(res / 255)  ## map it to 0..1
}


## the end of file
