lvls	<- levels(factor(HelloWorld$hello))
g		<- as.character(lvls)
data	<- (sapply(lvls, function(x){ sum(stringr::str_count(HelloWorld$hello, as.character(x))) }) / length(HelloWorld$hello))
pie		<- plotPieChart(data, g)

writeImage(plot=pie, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

