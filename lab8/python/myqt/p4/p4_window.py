from myqt.default.paragraph_window import *
from myqt.p4.p4_reader_window import P4ReaderWindow
from myqt.p4.p4_analyzer_window import P4AnalyzerWindow


class P4Window(PWindow):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        # Define available windows to switch
        self.p_reader = P4ReaderWindow(self)
        self.p_analyzer = P4AnalyzerWindow(self)

    def go_to_reader_window(self):
        self.hide()
        self.p_reader.show()

    def go_to_analyzer_window(self):
        self.hide()
        self.p_analyzer.show()
