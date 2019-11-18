// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visual.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/11/01 11:38:14 by agelloz           #+#    #+#             //
//   Updated: 2019/11/18 19:47:49 by agelloz          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var cy;
var data;
var ants_out = 0;
var ants_total = 0;

$(document).ready(function() {
	$.getJSON("data.json", function(data) {
		cy = cytoscape({
			container: $("#cy"),
			elements: data,
			layout: { name: "cose-bilkent" },
			style: [
				{
					selector: "node",
					style: {
						content: "data(id)",
						"font-size": "10px",
						"font-family": "Monaco",
						"text-valign": "center",
						"text-halign": "center",
						"background-color": "#232b2b",
						color: "#fff",
						"overlay-padding": "6px",
						"z-index": "10",
						opacity: "0.3"
					}
				},
				{
					selector: "edge",
					style: {
						opacity: "0.1",
						"line-color": "#353839",
						"overlay-padding": "3px"
					}
				}
			]
		});
		cy.elements('node[type = "start"]').style("background-color", "#ffffff");
		cy.elements('node[type = "start"]').style("border-style", "solid");
		cy.elements('node[type = "start"]').style("border-color", "#00ff00");
		cy.elements('node[type = "start"]').style("border-width", "5px");
		cy.elements('node[type = "start"]').style("color", "#000000");
		cy.elements('node[type = "start"]').style("opacity", "1");
		cy.elements('node[type = "end"]').style("background-color", "#ffffff");
		cy.elements('node[type = "end"]').style("border-style", "solid");
		cy.elements('node[type = "end"]').style("border-color", "#ff0000");
		cy.elements('node[type = "end"]').style("border-width", "5px");
		cy.elements('node[type = "end"]').style("color", "#000000");
		var width = cy.nodes('node[type = "start"]').style().width;
		var new_width = width.substr(0, width.length - 2) * 1.3 + "px";
		cy.nodes('node[type = "start"]').style("width", new_width);
		cy.nodes('node[type = "start"]').style("height", new_width);
		cy.nodes('node[type = "end"]').style("width", new_width);
		cy.nodes('node[type = "end"]').style("height", new_width);
		var i = 0;
		data.paths.forEach(function(path) {
			ants_total += path.ants;
			color_path(path.nodes, i);
			i++;
		});

		$("#next").click(function() {
			if (ants_out < ants_total) {
				data.paths.forEach(function(path) {
					path.nodes.forEach(function(node, i) {
						console.log(node);
						console.log(i);
						console.log(getComputedStyle(cy.elements('node[id = "' + node + '"]')).opacity);
						if (i != 0 && cy.nodes('node[id = "' + node + '"]').style.opacity == 1) {
							let_ant_pass(node, path.nodes[i + 1]);
						}
					});
					if (path.ants > 0 && cy.nodes('node[id = "' + path.nodes[1] + '"]').style.opacity != 1) {
						let_ant_pass(path.nodes[0], path.nodes[1]);
						path.ants -= 1;
					}
				});
			}
		});

	});
});

function let_ant_pass(node1, node2) {
	cy.nodes('node[id = "' + node2 + '"]').style("opacity", 1);
	cy.edges().filter(function(edge) {
		var e1 =
			edge.source().id() == node1 &&
			edge.target().id() == node2;
		var e2 =
			edge.source().id() == node2 &&
			edge.target().id() == node1;
		return e1 || e2;
	}).style("opacity", 1);
}

function color_path(nodes, i) {
	var j;
	var color;

	color = get_path_color(i);
	for (j = 0; j < nodes.length; j++) {
		if (
			nodes[j] != cy.nodes('node[type = "start"]').id() &&
			nodes[j] != cy.nodes('node[type = "end"]').id()
		) {
			room = nodes[j];
			cy.nodes('node[id = "' + nodes[j] + '"]').style(
				"background-color",
				color
			);
		}
		cy.edges().filter(function(edge) {
			var e1 =
				edge.source().id() == nodes[j] &&
				edge.target().id() == nodes[j + 1];
			var e2 =
				edge.source().id() == nodes[j + 1] &&
				edge.target().id() == nodes[j];
			return e1 || e2;
		}).style("line-color", color).style("opacity", 0.03);
	}
}

function get_path_color(i) {
	var color;

	if (i % 5 == 0) color = "#00aba9";
	else if (i % 5 == 1) color= "#ff0097";
	else if (i % 5 == 2) color = "#a200ff";
	else if (i % 5 == 3) color = "#1ba1e2";
	else if (i % 5 == 4) color = "#f09609";
	return color;
}
