// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visual.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/11/01 11:38:14 by agelloz           #+#    #+#             //
//   Updated: 2019/11/03 16:10:15 by agelloz          ###   ########.fr       //
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
								'background-color': '#555',
								'color': '#fff',
								'overlay-padding': '6px',
								'z-index': '10'
							}
						}, {
							selector: 'edge',
							style: {
								'opacity': "0.4",
								'line-color': "#bbb",
								'overlay-padding': "3px"
							}
						}]
					});
				cy.elements('node[type = "start"]').style('background-color', '#008744');
				cy.elements('node[type = "end"]').style('background-color', '#d62d20');
			});
	});
