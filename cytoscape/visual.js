// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visual.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/11/01 11:38:14 by agelloz           #+#    #+#             //
//   Updated: 2019/11/03 19:43:20 by agelloz          ###   ########.fr       //
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
						[{
							selector: 'node',
							style: {
								'content': 'data(id)',
								'font-size': '12px',
								'text-valign': 'center',
								'text-halign': 'center',
								'background-color': '#232b2b',
								'color': '#fff',
								'overlay-padding': '6px',
								'z-index': '10',
								'opacity': '0.6'
							}
						}, {
							selector: 'edge',
							style: {
								'opacity': '0.1',
								'line-color': '#353839',
								'overlay-padding': '3px'
							}
						}]
					});
				cy.elements('node[type = "start"]').style('background-color', '#ffffff');
				cy.elements('node[type = "start"]').style('border-style', 'solid');
				cy.elements('node[type = "start"]').style('border-color', '#00ff00');
				cy.elements('node[type = "start"]').style('border-width', '5px');
				cy.elements('node[type = "start"]').style('color', '#000000');
				cy.elements('node[type = "start"]').style('opacity', '1');
				cy.elements('node[type = "end"]').style('background-color', '#ffffff');
				cy.elements('node[type = "end"]').style('border-style', 'solid');
				cy.elements('node[type = "end"]').style('border-color', '#ff0000');
				cy.elements('node[type = "end"]').style('border-width', '5px');
				cy.elements('node[type = "end"]').style('color', '#000000');
				var width = cy.nodes('node[type = "start"]').style().width;
				var new_width = width.substr(0, width.length-2) * 1.3 + 'px';
				cy.nodes('node[type = "start"]').style('width', new_width);
				cy.nodes('node[type = "start"]').style('height', new_width);
				cy.nodes('node[type = "end"]').style('width', new_width);
				cy.nodes('node[type = "end"]').style('height', new_width);
				var i = 0;
				data.paths.forEach(function(p) {
					print_path(p.path_nodes, i);
					i++;
				});
			});
	});

var colors = [];
var color = '#000000';

function        print_path(path_nodes, i)
{
	color = getColor(i);
	colors.push({'path': path_nodes, 'color': color});
	var j;
	for (j = 0; j < path_nodes.length; j++)  {
		if (path_nodes[j] != cy.nodes('node[type = "start"]').id()
			&& path_nodes[j] != cy.nodes('node[type = "end"]').id()) {
			room = path_nodes[j];
			cy.nodes('node[id = "' + path_nodes[j] + '"]').style('background-color', color[0]);
		}
		tunnel = cy.edges().filter(function(edge) {
			var e1 = (edge.source().id() == path_nodes[j] && edge.target().id() == path_nodes[j + 1]);
			var e2 = (edge.source().id() == path_nodes[j + 1] && edge.target().id() == path_nodes[j]);
			return e1 || e2;
		});
		tunnel.style('line-color', color[0]);
	}
}

function        getColor(i)
{
	var tmp_colors = [];

	if (i % 5 == 0)
		tmp_colors[0] = '#00aba9';
	else if (i % 5 == 1)
		tmp_colors[0] = '#ff0097';
	else if (i % 5 == 2)
		tmp_colors[0] = '#a200ff';
	else if (i % 5 == 3)
		tmp_colors[0] = '#1ba1e2';
	else if (i % 5 == 4)
		tmp_colors[0] = '#f09609';
	tmp_colors[1] = tmp_colors[0];
	return tmp_colors;
}
