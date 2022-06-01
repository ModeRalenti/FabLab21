
// fonction qui ajoute un point sur le graphe plotly (pour un affichage temps réel)
function affichePoint() {
	var update = {
	x:  [[temps]],
	y: [[Eclairement]]
	}
	Plotly.extendTraces('graph', update, [0])
}


function departstop() {
	if (AffichePoints){
		AffichePoints = false;
		
	}else {
		//effaceGraphe();
		AffichePoints = true;
		//depart=true;// pour effectuer remise à zéro du temps
	}
}// fin depart-stop

function effaceGraphe(){
	data = [{
	x: [], 
	y: [],
	mode: 'lines+markers',
	marker: {
    color: 'red',
    size: 6,
    //line: {
    //  color: 'rgb(231, 99, 250)',
    //  width: 2
    //},
	},
	line: {shape: 'spline', color: '#80CAF6'}

	}]
	depart=true;// pour effectuer remise à zéro du temps
	AffichePoints = false;// arrêt du tracé
	Plotly.newPlot('graph', data, layout,{responsive: true,displaylogo: false});
	csvdata = [];
};// fin effacegraphe

function lignepoints(){
	if (LignePoints) {
		//update the layout and all the traces
		var layout_update = {
		title: 'Acquisition (tracé ligne lissée spline)', // updates the title
		};
		var data_update = {
		'marker.color': 'red',
		mode :'lines',
		line: {shape: 'spline', color: '#80CAF6'}
		};
		LignePoints = false;
	}else {
		var layout_update = {
		title: 'Acquisition (tracé avec points et lignes )', // updates the title
		};
		var data_update = {
		'marker.color': 'red',
		mode :'lines+markers',
		line: {shape: 'line', color: '#80CAF6'}
		};
		LignePoints =true;
		
	}

	Plotly.update('graph', data_update, layout_update);
}// fin lignepoints

// création du fichier csv
function download_csv() {
	console.log("taille du tableau de données : "+csvdata.length);
	if (csvdata.length > 4){
		var csv = 'temps (s);Eclairement (lx)\n';
		//console.log(csv);
		csvdata.forEach(function(row) {
				csv += row.join(';');
				csv += "\n";
		});
	 
		console.log(csv);
		var hiddenElement = document.createElement('a');
		hiddenElement.href = 'data:text/csv;charset=utf-8,%EF%BB%BF' + encodeURI(csv);//utf-8 BOM
		hiddenElement.target = '_blank';
		hiddenElement.download = 'Donnees.csv';
		hiddenElement.click();
	}else{
		console.log("taille du tableau de données trop petite ! "+csvdata.length+ " < 5");
	}
}
function currencyFormatFR(num) {
  return (
    num
      .toFixed(2) // always two decimal digits
      .replace('.', ',') // replace decimal point character with ,
      //.replace(/(\d)(?=(\d{3})+(?!\d))/g, '$1.')
  ) // use . as a separator
}

