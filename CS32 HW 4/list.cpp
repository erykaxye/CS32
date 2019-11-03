void listAll(const Class* c, string path)  // two-parameter overload
{
	cout << path + c->name() << endl;
	if (c->subclasses().size() == 0)
		return;
	vector<Class*>::const_iterator it;
	for (it = c->subclasses().begin(); it != c->subclasses().end(); it++)
		listAll(*it, path + c->name() + "=>");
}