\name{sobel.h}
\alias{sobel.h}
\title{sobel filter to extract horizontal edges}
\description{
  This function calculates an image which sobel filter is applied.
  It extracts horizontal edges only.  It is faster than sobel.h
  extremely because utilization of a C routine.
}
\usage{sobel.h(img)}
\arguments{
  \item{img}{a matrix representing target image}
}
\value{
  a matrix representing the image after horizontal sobel filter is applied 
}
\examples{
  data(logo)
  plot(normalize(sobel.h(logo)))
}
\seealso{\code{\link{sobel.v}},\code{\link{sobel}}}
\keyword{misc}