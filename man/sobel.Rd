\name{sobel}
\alias{sobel}
\title{Sobel filter}
\description{
  This function calculates an image which sobel filter is applied.
  It utilizes a C routine for improving speed.
}
\usage{sobel(img)}
\arguments{
  \item{img}{a matrix representing target image}
}
\value{
  a matrix representing the image after sobel filter is applied 
}
\examples{
  data(logo)
  plot(normalize(sobel(logo)))
}
\seealso{\code{\link{sobel.h}},\code{\link{sobel.v}},\code{\link{imagematrix}}}
\keyword{misc}
