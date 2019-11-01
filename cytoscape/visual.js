// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visual.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/11/01 11:38:14 by agelloz           #+#    #+#             //
//   Updated: 2019/11/01 12:01:28 by agelloz          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var cy;
var data;

$(document).ready(
	function()
	{
		$.getJSON("data.json", function(data) 
			{	
				cy = cytoscape(
					{
						container: $("#cy"),
						elements: data,
						layout: { name: 'cose-bilkent' },
						style: 
						[
							{ selector: 'node', style: { 'background-color': '#666', 'label': 'data(id)' } },
							{
								selector: 'edge',
								style: { 'width': 3, 'line-color': '#ccc', 'target-arrow-color': '#ccc', 'target-arrow-shape': 'triangle' }
							}
						]
					});
				cy.elements('node[type = "start"]').style('background-color', 'green');
				cy.elements('node[type = "end"]').style('background-color', 'red');
			});

		$("#play_pause_button").click(function() {
			pause = false;
			play();
		});

		function play() {
			var timeOut;
			if (data.moves.length > 50)
				timeOut = 10;
			else if (data.moves.length > 20)
				timeOut = 200;
			else
				timeOut = 500;
			if (antsOut != data.ant_qty && pause == false) {
				setTimeout(function() {
					$("#next").trigger("click");
					play_button();
				}, timeOut);
			} else {
				cy.edges().forEach(function(edge) {
					edge.style('line-color', 'white');
				});
			}
		}
	});
