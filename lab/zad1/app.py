from time import time
import os
import tornado.ioloop
import tornado.web
import json

class Tree:
	def __init__(self, id, data):
		self.id = id
		self.p = data[0]
		self.d = data[1]
		self.w = data[2]

	def __repr__(self):
		return str(self.id)
		#return "(p=%s, d=%s, w=%s)" % (self.p, self.d, self.w)

def countTWT(tree):
	tree = list(tree)

	c = 0
	value = 0

	for i in range(0, len(tree)):
		c += tree[i].p
		t = c-tree[i].d
		if t > 0:
			value += t * tree[i].w

	return value

def kryt_1(value, min_value):
	if value > min_value:
		return False
	return True

def kryt_2(follow, value):
	follow = list(follow)
	for j in range(1, len(follow)):
		follow[-j], follow[-1-j] = follow[-1-j], follow[-j]
		#count
		currentValue = countTWT(follow)
		if currentValue < value:
			return False

	follow.append(follow.pop(0))
	return True

def kryt_3():
	return True

def bab(input, i, follow, c, value, parent):
	global min_value

	input = list(input)
	follow = list(follow)

	follow.append(input[i]);

	c += input[i].p
	t = c-input[i].d
	if t > 0:
		value += t * input[i].w

	parent['data']['about'] = "c=%d value=%d" % (c, value)

	# pierwsze kryterium eliminacyjne
	if not kryt_1(value, min_value):
		return

	# drugie kryterium eliminacyjne
	if not kryt_2(follow, value):
		return

	# trzecie kryterium eliminacyjne
	if not kryt_3():
		return

	del input[i]

	if len(input) > 0:
		for j in range(len(input)):
			parent['children'].append({'id': str(parent['id'])+str(input[j].id), 'children':[], 'data':{}, 'name': str(input[j].id)})
			bab(input, j, follow, c, value, parent['children'][j])
	else:
		global min_tree

		if value < min_value:
			min_tree = follow
			min_value = value

min_value = 999999999
min_tree = []

def start(file):
	# read file
	tasks = [Tree(0, [0,0,0]),]
	i = 1
	for o in [[int(x) for x in line.split()] for line in open('../data'+str(file)+'.txt')]:
		tasks.append(Tree(i, o))
		i+=1

	start = time()
	root = {'id': 'node02', 'children':[], 'data':{'about':'root'}, 'name':'root'}
	bab(tasks, 0, [], 0, 0, root)
	end = time()

	print file
	print "time = %f sec" % (end-start, )
	print "min_value = %d" % (min_value, )
	print min_tree
	return {'tree': root, 'result': "t=%fs, min=%d" % (end-start,min_value)}

class JsonHandler(tornado.web.RequestHandler):
	def get(self):
		global file
		data = start(file)
		self.write(json.dumps(data))

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
		global file
		if self.get_argument("file", None) != None:
			file = self.get_argument("file")
			self.render('index.html')
		self.render('select.html')

application = tornado.web.Application([
	(r"/", IndexHandler),
	(r"/json", JsonHandler),
	(r"/static/(.*?)", tornado.web.StaticFileHandler, {
		"path": os.path.join(os.path.dirname(__file__), "static")
	}),
])

if __name__ == "__main__":
    application.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
    #start(12)
