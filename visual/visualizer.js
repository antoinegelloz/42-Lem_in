// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visualizer.js                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/11/01 11:38:14 by agelloz           #+#    #+#             //
//   Updated: 2019/11/29 18:53:03 by agelloz          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var cy;
var data;
var ants_out = 0;
var ants_total = 0;
var rounds = 0;
var pause = true;
var time_out = 0;

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
						"line-color": "#353839",
						"overlay-padding": "3px",
						"curve-style": "straight",
						opacity: "0.03"
					}
				}
			]
		});
		var width = cy.nodes('node[type = "start"]').style("width");
		var new_width = width.substr(0, width.length - 2) * 1.3 + "px";
		cy.nodes('node[type = "start"]').style({
			"background-color": "#ffffff",
			"border-style": "solid",
			"border-color": "#00ff00",
			"border-width": "5px",
			color: "#000000",
			opacity: "1",
			width: new_width,
			height: new_width
		});
		cy.nodes('node[type = "end"]').style({
			"background-color": "#ffffff",
			"border-style": "solid",
			"border-color": "#ff0000",
			"border-width": "5px",
			color: "#000000",
			width: new_width,
			height: new_width
		});
		var i = 0;
		var all_started;
		var ants_on_paths = new Array(data.paths.length);

		$("#paths").text("Paths: " + data.paths_count);
		$("#ants_out").text("Ants out: " + ants_out + "/" + data.ants);
		$("#rounds").text("Rounds: " + rounds);
		data.paths.forEach(function(path, p) {
			ants_total += path.ants;
			color_path(path.nodes, i);
			ants_on_paths[p] = path.ants;
			i++;
		});

		$("#next").click(function() {
			if (ants_out < ants_total) {
				all_started = true;
				data.paths.forEach(function(path, p) {
					for (i = path.nodes.length - 2; i > 0; i--) {
						if (cy.getElementById(path.nodes[i]).style("opacity") == 1) {
							move_ant(path.nodes[i], path.nodes[i + 1], data.ants);
							for (i = 1; i < path.nodes.length; i++) {
								if (get_edge_opacity(path.nodes[i - 1], path.nodes[i]) == 1) {
									cy.getElementById(path.nodes[i]).style("opacity", 0.3);
									set_edge_opacity(path.nodes[i - 1], path.nodes[i], 0.03);
									break;
								}
							}
							break;
						}
					}
					if (
						ants_on_paths[p] > 0 &&
						get_edge_opacity(path.nodes[0], path.nodes[1]) < 1
					) {
						move_ant(path.nodes[0], path.nodes[1], data.ants);
						ants_on_paths[p] -= 1;
						if (ants_on_paths[p] > 0) {
							all_started = false;
						}
					}
				});
				if (all_started == true) {
					cy.nodes('node[type = "start"]').style("opacity", 0.3);
				}
				rounds += 1;
				$("#rounds").text("Rounds: " + rounds);
			} else {
				cy.nodes().style("opacity", 0.3);
				cy.edges().style("opacity", 0.03);
				cy.nodes('node[type = "end"]').style("opacity", 1);
				document.getElementById("play_pause").style.color = "#999999";
				document.getElementById("next").style.color = "#999999";
			}
		});

		$("#reset").click(function() {
			if (pause == false)
			{
				pause = true;
				$("#play_pause").text("Play ");
			}
			ants_out = 0;
			rounds = 0;
			$("#ants_out").text("Ants out: " + ants_out + "/" + data.ants);
			$("#rounds").text("Rounds: " + rounds);
			data.paths.forEach(function(path, p) {
				for (i = 0; i < path.nodes.length; i++) {
					cy.getElementById(path.nodes[i]).style("opacity", 0.3);
					set_edge_opacity(path.nodes[i], path.nodes[i + 1], 0.03);
				}
				ants_on_paths[p] = path.ants;
			});
			cy.nodes('node[type = "start"]').style("opacity", 1);
			cy.nodes('node[type = "end"]').style("opacity", 0.3);
			document.getElementById("play_pause").style.color = "#111111";
			document.getElementById("next").style.color = "#111111";
		});

		$("#play_pause").click(function() {
			if (pause == true) {
				pause = false;
				$("#play_pause").text("Pause");
			} else {
				pause = true;
				$("#play_pause").text("Play ");
			}
			play_pause();
		});
	});
});

function play_pause() {
	if (ants_out <= ants_total && pause == false) {
		time_out = 80;
		setTimeout(function() {
			$("#next").trigger("click");
			play_pause();
		}, time_out);
		if (ants_out == ants_total) {
			$("#play_pause").trigger("click");
		}
	}
}

function set_edge_opacity(node1, node2, value) {
	cy.edges()
		.filter(function(edge) {
			var e1 = edge.source().id() == node1 && edge.target().id() == node2;
			var e2 = edge.source().id() == node2 && edge.target().id() == node1;
			return e1 || e2;
		})
		.style("opacity", value);
}

function get_edge_opacity(node1, node2) {
	return cy
		.edges()
		.filter(function(edge) {
			var e1 = edge.source().id() == node1 && edge.target().id() == node2;
			var e2 = edge.source().id() == node2 && edge.target().id() == node1;
			return e1 || e2;
		})
		.style("opacity");
}

function move_ant(node1, node2, total_ants) {
	cy.nodes('node[id = "' + node2 + '"]').style("opacity", 1);
	set_edge_opacity(node1, node2, 1);
	//console.log(node1 + "->" + node2);
	if (node2 == cy.nodes('node[type = "end"]').id()) {
		ants_out += 1;
		$("#ants_out").text("Ants out: " + ants_out + "/" + total_ants);
	}
}

function color_path(nodes, i) {
	var j;
	var color;

	if (i % 5 == 0) color = "#00aba9";
	else if (i % 5 == 1) color = "#ff0097";
	else if (i % 5 == 2) color = "#a200ff";
	else if (i % 5 == 3) color = "#1ba1e2";
	else if (i % 5 == 4) color = "#f09609";
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
		cy.edges()
			.filter(function(edge) {
				var e1 =
					edge.source().id() == nodes[j] && edge.target().id() == nodes[j + 1];
				var e2 =
					edge.source().id() == nodes[j + 1] && edge.target().id() == nodes[j];
				return e1 || e2;
			})
			.style("line-color", color)
			.style("opacity", 0.03);
	}
}
