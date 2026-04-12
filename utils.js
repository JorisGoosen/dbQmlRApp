function resizePlot(w, h, g=18)
{
    var hetPlot = document.getElementById("het_plot");
    if (!hetPlot)	
    {
        console.log("Resize failed because there is no plot?")
        return;
    }
    
    w -= g
    h -= g    
    
    console.log("Resizing plot to:", w, h);

    hetPlot.style.width  = w + 'px';
    hetPlot.style.height = h + 'px';
    
    if (hetPlot.data) 
    {
        Plotly.relayout(hetPlot, {
            width: w,
            height: h
        }).catch(function(err) {
            console.warn("Plotly relayout failed:", err);
        });
    }
}
