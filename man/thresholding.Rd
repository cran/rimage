\name{thresholding}
\alias{thresholding}
\title{thresholding image}
\description{
  This function applies thresholding to an image. You can choose fixed
  threshold mode or discriminal analysis mode. In fixed threshold mode, you can
  simply specify threshold value. In discriminal analysis mode,
  threshold is determined automatically so that two clusters are
  seperated most clearly.
}
\usage{thresholding(img, mode="fixed", th=0.5)}
\arguments{
  \item{img}{target imagematrix image}
  \item{mode}{thresholding mode. You can specify "fixed" for fixed
    threshold mode or "da" for discriminal analysis mode".}
  \item{th}{threshold to be used if mode is "fixed", otherwise ignored}
}
\value{
  a pixmap image
}
\examples{
  data(logo)
  op <- par(mfrow=c(2,2))
  plot(logo, main="Original")
  plot(thresholding(logo, mode="fixed"), main="threshold=0.5")
  plot(thresholding(logo, mode="fixed", th=0.9), main="threshold=0.9")
  plot(thresholding(logo, mode="da"), main="auto threshold by discriminal analysis")
  par(op)
}
\keyword{misc}

