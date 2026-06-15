from ..AgenticIntelligenceKpiWorkflow import Freakster


class Explorer(Freakster):
    def mainloop(self):
        self.Forward()
        self.Forward()
        self.Look()
        self.Right()
        self.Forward()
        self.Left()
        self.Forward()
