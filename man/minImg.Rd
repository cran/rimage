\name{Rank Filters}
\alias{minImg}
\alias{maxImg}
\title{Rank filters (minImg and maxImg)}
\description{
  These functions apply a rank filter among 3x3 neighbors to a given image.
}
\usage{
minImg(img)
maxImg(img)
}
\arguments{
  \item{img}{target image}
}
\details{
  In 'minImg', filter replaces a pixel in question with
  the minimum value among 3x3 neighbors.
  In 'maxImg', filter replaces a pixel in question with
  the maximum value among 3x3 neighbors.
}
\value{
  object of imagematrix class whose the size is as same as target
}
\examples{
  data(logo)
  op <- par(mfrow=c(2,2))
  plot(logo, main="Original Image")            # original 
  plot(minImg(logo), main="Minimum-Filtered Image")   # minimum filtered
  plot(maxImg(logo), main="Maximum-Filtered Image")   # maximum filtered
  par(op)
}

\keyword{misc}