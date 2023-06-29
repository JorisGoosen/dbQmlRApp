lvls	<- levels(factor(SchoolScanner$school))
g		<- as.character(lvls)
data	<- (sapply(lvls, function(x){ sum(stringr::str_count(SchoolScanner$school, as.character(x))) }) / length(SchoolScanner$school))
pie		<- plotPieChart(data, g)

writeImage(plot=pie, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

print(SchoolScanner)
