\name{sobel.v}
\alias{sobel.v}
\title{Sobel filter to extract vertical edges}
\description{
  This function calculates an image which sobel filter is applied.
  It extracts vertical edges only. It is faster than sobel.v
  extremely because utilization of a C routine.
}
\usage{sobel.v(img)}
\arguments{
  \item{img}{a matrix representing target image}
}
\value{
  a matrix representing the image after vertical sobel filter is applied 
}
\examples{
  data(logo)
  plot(normalize(sobel.v(logo)))
}
\seealso{\code{\link{sobel.h}},\code{\link{sobel}}}
\keyword{misc}
