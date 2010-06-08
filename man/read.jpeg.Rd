\name{read.jpeg}
\alias{read.jpeg}
\title{Read JPEG file}
\description{
  This function reads a jpeg image file and return an imagematrix object.
}
\usage{read.jpeg(filename)}
\arguments{
  \item{filename}{filename of JPEG image}
}
\value{
  return an imagematrix object
}
\examples{
  x <- read.jpeg(system.file("images", "cat.jpg", package="rimage"))
  plot(x)
}
\seealso{\code{\link{imagematrix}}}
\keyword{misc}


