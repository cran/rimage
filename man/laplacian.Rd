\name{laplacian}
\alias{laplacian}
\title{Laplacian of image}
\description{
  Calculate 2nd derivative of image for edge extraction
}
\usage{
laplacian(img)
}
\arguments{
  \item{img}{target image}
}
\value{
  an object of pixmap class whose the size is as same as target
}
\examples{
  data(logo)
  plot(normalize(laplacian(logo)))
}
\keyword{misc}
