lvls	<- levels(factor(SchoolScannerTextOnly$school))
g		<- as.character(lvls)
data	<- (sapply(lvls, function(x){ sum(stringr::str_count(SchoolScannerTextOnly$school, as.character(x))) }) / length(SchoolScannerTextOnly$school))
pie		<- plotPieChart(data, g)

writeImage(plot=pie, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

#print(SchoolScannerTextOnly)
