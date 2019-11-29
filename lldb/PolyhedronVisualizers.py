

class Vec_SyntheticChildrenProvider():
    def __init__(self, valobj, internal_dict):
        # Initialize the Python object using valobj as the variable to provide synthetic children.
        self.sbValObject = valobj

    def num_children(self):
        # Return the number of children you want your object to have.
        return 3

    def get_child_index(self,name):
        # Return the index of the synthetic child whose name is given as argument.
        if name == "x":
            return 0
        elif name == "y":
            return 1
        elif name == "z":
            return 2

        return None
        
    def get_child_at_index(self,index):
        # Return a new LLDB SBValue object representing the child at the index given as argument.
        if index == 0:
            return self.sbValObject.GetChildMemberWithName("x")
        elif index == 1:
            return self.sbValObject.GetChildMemberWithName("y")
        elif index == 2:
            return self.sbValObject.GetChildMemberWithName("z")
        else:
            return None

    def update(self):
        # Update the internal state of this Python object whenever the state of the variables in LLDB changes.
        pass

    def has_children(self):
        # Return True if this object might have children and False if this object can be guaranteed to not have children.
        return True

    def get_value(self):
        # Return an SBValue to be presented as the value of the synthetic value under consideration.
        return self.sbValObject


class Vec2_SyntheticChildrenProvider():
    def __init__(self, valobj, internal_dict):
        # Initialize the Python object using valobj as the variable to provide synthetic children.
        self.sbValObject = valobj

    def num_children(self):
        # Return the number of children you want your object to have.
        return 2

    def get_child_index(self,name):
        # Return the index of the synthetic child whose name is given as argument.
        if name == "x":
            return 0
        elif name == "y":
            return 1

        return None
        
    def get_child_at_index(self,index):
        # Return a new LLDB SBValue object representing the child at the index given as argument.
        if index == 0:
            return self.sbValObject.GetChildMemberWithName("x")
        elif index == 1:
            return self.sbValObject.GetChildMemberWithName("y")
        else:
            return None

    def update(self):
        # Update the internal state of this Python object whenever the state of the variables in LLDB changes.
        pass

    def has_children(self):
        # Return True if this object might have children and False if this object can be guaranteed to not have children.
        return True

    def get_value(self):
        # Return an SBValue to be presented as the value of the synthetic value under consideration.
        return self.sbValObject


class Vec4_SyntheticChildrenProvider():
    def __init__(self, valobj, internal_dict):
        # Initialize the Python object using valobj as the variable to provide synthetic children.
        self.sbValObject = valobj

    def num_children(self):
        # Return the number of children you want your object to have.
        return 4

    def get_child_index(self,name):
        # Return the index of the synthetic child whose name is given as argument.
        if name == "x":
            return 0
        elif name == "y":
            return 1
        elif name == "z":
            return 2
        elif name == "w":
            return 3

        return None
        
    def get_child_at_index(self,index):
        # Return a new LLDB SBValue object representing the child at the index given as argument.
        if index == 0:
            return self.sbValObject.GetChildMemberWithName("x")
        elif index == 1:
            return self.sbValObject.GetChildMemberWithName("y")
        elif index == 2:
            return self.sbValObject.GetChildMemberWithName("z")
        elif index == 3:
            return self.sbValObject.GetChildMemberWithName("w")
        else:
            return None

    def update(self):
        # Update the internal state of this Python object whenever the state of the variables in LLDB changes.
        pass

    def has_children(self):
        # Return True if this object might have children and False if this object can be guaranteed to not have children.
        return True

    def get_value(self):
        # Return an SBValue to be presented as the value of the synthetic value under consideration.
        return self.sbValObject