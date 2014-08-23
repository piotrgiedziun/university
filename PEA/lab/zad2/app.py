#!/usr/bin/python
import math, os, sys, argparse
from random import randint as random
from time import time as timer

class Task:
	def __init__(self, id, time):
		self.id = id+1
		self.time = time

	def __repr__(self):
		return "id=%d t=%d" % (self.id, self.time)

def rec(tasks, lines):
	task = tasks[len(lines)-1]

	before = lines[-1]
	new_line = list(lines[-1])

	current_time = 0

	for i in before:
		if i == "T" and task.time+current_time<len(before):
			new_line[task.time+current_time] = "T"
		current_time += 1

	lines.append(new_line)

	if len(lines) > len(tasks):
		return lines

	return rec(tasks, lines)

def back(output, tasks, pos, results):
	for line_id in range(0, len(output)):
		if output[line_id][pos] ==  "T":
			results.append(tasks[line_id-1])
			if pos-tasks[line_id-1].time <= 0:
				return results

			return back(output, tasks, pos-tasks[line_id-1].time, results)

def main(args):
	tasks = []
	task_time = 0

	for time in open('input.txt'):
		tasks.append(Task(len(tasks), int(time)))
		task_time += int(time)

	time_start = timer()
	p2_time = math.floor(task_time/2)
	table = [[" "] * int(p2_time+1),]
	table[0][0] = "T"

	output = rec(tasks, table)

	results = []
	back(output, tasks, int(p2_time), results)
	time_end = timer()

	p1 = sorted(results, key=lambda x: x.id, reverse=False)
	p2 = sorted(list(set(tasks)-set(p1)), key=lambda x: x.id, reverse=False)

	# generate HTML output
	if not args.output_json:
		output_html_data = [{'count':0, 'tasks':[]},{'count':0, 'tasks':[]}]

		for task in p1:
			output_html_data[0]['count'] += task.time
		for task in p2:
			output_html_data[1]['count'] += task.time
		output_html_max = max(output_html_data[0]['count'], output_html_data[1]['count'])


		for task in p1:
			output_html_data[0]['tasks'].append({'id': task.id, 'time': task.time, 'width': round(task.time*100.0/output_html_max, 5)})
		for task in p2:
			output_html_data[1]['tasks'].append({'id': task.id, 'time': task.time, 'width': round(task.time*100.0/output_html_max, 5)})

		output_html = "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"
		output_html += "<center class=\"process_data\">Processor #1 - time "+str(output_html_data[0]['count'])+"</br>"
		output_html += "Processor #2 - time "+str(output_html_data[1]['count'])+"</center></br>"

		output_html += "<div class=\"processor\">"
		for task in output_html_data[0]['tasks']:
			r = random(0,255)
			g = random(0,255)
			b = random(0,255)
			output_html += "<div class=\"task\" onmouseover=\"tooltip.show('Task: "+str(task["id"])+"</br>Czas zadania "+str(task['time'])+"');\" onmouseout=\"tooltip.hide();\" style=\"color:rgb("+str(255-r)+","+str(255-g)+","+str(255-b)+");background-color:rgb("+str(r)+","+str(g)+","+str(b)+");width:"+str(task['width']*8)+"px\">"+str(task['id'])+"</div>"

		output_html += "</div><div class=\"processor\">"
		for task in output_html_data[1]['tasks']:
			r = random(0,255)
			g = random(0,255)
			b = random(0,255)
			output_html += "<div class=\"task\" onmouseover=\"tooltip.show('Task: "+str(task["id"])+"</br>Czas zadania "+str(task['time'])+"');\" onmouseout=\"tooltip.hide();\" style=\"color:rgb("+str(255-r)+","+str(255-g)+","+str(255-b)+");background-color:rgb("+str(r)+","+str(g)+","+str(b)+");width:"+str(task['width']*8)+"px\">"+str(task['id'])+"</div>"
		output_html += "</div>"

		# tooltip
		output_html += "<script type=\"text/javascript\" language=\"javascript\" src=\"script.js\"></script>"

		# time 
		output_html += "<div class=\"time\">Czas wykonania alogrytmu: %f sekund</div>" % (time_end-time_start,)
		
		# tabelka przejsc
		output_html += "<div id=\"table\"><div id=\"table2\"><table>"
		for i in range(0, len(tasks)+1):
			output_html += "<tr><td>"+str(i)+"</td></tr>"

		output_html += "</table></div><div id=\"table1\"><table>"
		for line in output:
			output_html += "<tr>"
			for elm in line:
				output_html += "<td>%s<td>" % (elm,)
			output_html += "</tr>"
		output_html += "</table></div></div>"


		f = open("index.html", "w")
		f.write(output_html)
		f.close()

		os.system("open index.html")
	else:
		p1_count = 0
		p2_count = 0
		for task in p1:
			p1_count += task.time
		for task in p2:
			p2_count += task.time

		print "%d\t%d\t%f" % (p1_count, p2_count, time_end-time_start)

parser = argparse.ArgumentParser()
parser.add_argument('-output_json', action="store_true", default=False)

main(parser.parse_args(sys.argv[1:]))