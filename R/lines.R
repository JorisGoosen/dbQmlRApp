lines	<- ggplot(HelloWorld, aes(x=id)) +
            geom_line(aes(y=world), color="yellow") +
			geom_line(aes(y=this),	color="blue") +
			geom_line(aes(y=isa),	color="white") +
			geom_line(aes(y=tafel), color="green") +
			jaspGraphs:::themeJaspRaw(legend.position="right")

writeImage(plot=lines, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

