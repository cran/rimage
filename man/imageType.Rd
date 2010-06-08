\name{imageType}
\alias{imageType}
\title{Get information on color type of imagematrix}
\description{
  This function returns color type ("rgb" or "grey") of
  a given imagematrix.
}
\usage{imageType(x)}
\arguments{
  \item{x}{target image}
}
\value{
  "rgb" or "grey"
}
\examples{
  x <- read.jpeg(system.file("images", "cat.jpg", package="rimage"))
  cat("Image Type", imageType(x))

  x.grey <- rgb2grey(x)
  cat("Image Type", imageType(x.grey))
}
\keyword{misc}


