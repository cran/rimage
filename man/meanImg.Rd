\name{meanImg}
\alias{meanImg}
\title{Mean filter}
\description{
  This function applies mean filter among 9 neighbors to a given image.
}
\usage{meanImg(img)}
\arguments{
  \item{img}{target image}
}
\value{
  object of imagematrix class whose the size is as same as target
}
\examples{
  data(logo)
  plot(meanImg(logo))
}
\keyword{misc}
