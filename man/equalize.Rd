\name{equalize}
\alias{equalize}
\title{Make image having equalized histogram}
\description{
  This function make image having equalized histogram of original image.
}
\usage{equalize(img)}
\arguments{
  \item{img}{target image}
}
\value{
  Data of the same mode as 'img', in which minimum value is 0 and maximum
  value is 1.
}
\examples{
  op <- par(mfrow=c(2,2))
  data(logo)

  plot(logo, main="Original Logo")
  plot(equalize(logo), main="Equalized Logo")

  catpic <- rgb2grey(read.jpeg(system.file("data", "cat.jpg", package="rimage")))
  plot(catpic, main="Cat Image in Greyscale")
  plot(equalize(catpic), main="Equalized Cat Image")

  par(op)
}
\keyword{misc}
