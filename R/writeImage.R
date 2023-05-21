library(jaspGraphs)
library(ggplot2)

#Taken from jaspBase and modified to be a bit simpler

tryToWriteImage <- function(...) {
  tryCatch(
    suppressWarnings(return(writeImage(...))),
	error	= function(e) { return(list(error = e$message)) }
  )
}

openGrDevice <- function(...) {
  ragg::agg_png(...)
}

writeImage <- function(plot, relativePathpng = "plot.png", width = 500, height = 500, ppi = 300, backgroundColor = "transparent")
{

    width  <- width  * (ppi / 96)
	height <- height * (ppi / 96)

    openGrDevice(file = relativePathpng, width = width, height = height, res = 72 * (ppi / 96), background = backgroundColor)
	on.exit(dev.off(), add = TRUE)

    if (ggplot2::is.ggplot(plot) || inherits(plot, c("gtable", "gTree")))
	{

        # inherited from ggplot2::ggsave
		grid::grid.draw(plot)

    }
	else
	{
	    isRecordedPlot <- inherits(plot, "recordedplot")

        if (is.function(plot) && !isRecordedPlot)
		{
		    if (obj) dev.control('enable')
			    eval(plot()) # enable plot recording

            if (obj)
			    plot <- recordPlot() # save plot to R object

        }
		else if (inherits(plot, "qgraph"))
		{
		    qgraph:::plot.qgraph(plot)
		}
		else
		{
		    plot(plot)
		}

    }

    return(file.path(getwd(),relativePathpng))
}

# This ensures that functions can also be found in jasptools (it needs to search in the package namespace)
.findFun <- function(name) {
  obj <- NULL
  if (exists(name))
    obj <- eval(parse(text = name))

  if (!exists(name) || !is.function(obj)) {

    if ("jasptools" %in% loadedNamespaces())
	  return(getFromNamespace(name, asNamespace("jasptools")))
	return(get(name, .GlobalEnv)) # works for both JASP and jaspTools
  }

  if (!is.function(obj))
    return(NULL)

  return(obj)
}
