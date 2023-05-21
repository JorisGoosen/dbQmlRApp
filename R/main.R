lvls	<- levels(factor(HelloWorld$hello))
g		<- as.character(lvls)
data	<- (sapply(lvls, function(x){ sum(stringr::str_count(HelloWorld$hello, as.character(x))) }) / length(HelloWorld$hello))
pie		<- plotPieChart(data, g)

lines	<- ggplot(HelloWorld, aes(x=id)) +
            geom_line(aes(y=world), color="yellow") +
			geom_line(aes(y=this),	color="blue") +
			geom_line(aes(y=isa),	color="white") +
			geom_line(aes(y=tafel), color="green") +
			jaspGraphs:::themeJaspRaw(legend.position="right")

c(
    writeImage(plot=pie,	relativePathpng = "pie.png",	width=WIDTH, height=HEIGHT),
	writeImage(plot=lines,	relativePathpng = "lines.png",	width=WIDTH, height=HEIGHT)
)
