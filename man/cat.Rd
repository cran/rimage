\name{cat.picture}
\alias{cat.picture}
\title{JPEG picture of a cat}
\description{
JPEG file of a cat.
}
\usage{data(cat)}
\format{JPEG}
\source{Original photograph taken by a member of rimage developer.}
\examples{
  x <- read.jpeg(system.file("data", "cat.jpg", package="rimage"))
  plot(x)
}
\seealso{\code{\link{read.jpeg}}}
\keyword{datasets}


