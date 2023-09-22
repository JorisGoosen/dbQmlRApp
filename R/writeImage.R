library(jaspGraphs)
library(ggplot2)
library(tidyr)
library(ggplot2)
library(stringr)

kleuren <- list(
  lichtrozig=		"#f6b6cc"	,
  rozig=			"#EF2560"	,
  lichtblauwig=		"#9CCDD1"	,
  blauwig=			"#038794"	,
  zwartig=			"#1D1D1B"	,
  lichtgroen=		"#BCE2D7"	,
  donkergroen=		"#5FA48F"	,
  lichtgeel=		"#FFF798"
)

library(showtext)
font_add_google("Karla", "karla")

## Automatically use showtext to render text
showtext_auto()


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

writeImage <- function(plot, plotFolder=".", plotFile = "plot.png", width = 500, height = 500, ppi = 200, backgroundColor = "transparent")
{

    width  <- width  * (ppi / 96)
	height <- height * (ppi / 96)

    oldWd <- getwd();
	setwd(plotFolder);

    openGrDevice(file = plotFile, width = width, height = height, res = 72 * (ppi / 96), background = backgroundColor)
	on.exit({dev.off(); setwd(oldWd)}, add = TRUE)

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

    return(plotFile)
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
