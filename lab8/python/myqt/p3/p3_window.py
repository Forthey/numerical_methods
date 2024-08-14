from myqt.default.paragraph_window import *
from myqt.p3.p3_reader_window import P3ReaderWindow
from myqt.p3.p3_analyzer_window import P3AnalyzerWindow


class P3Window(PWindow):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        # Define available windows to switch
        self.p_reader = P3ReaderWindow(self)
        self.p_analyzer = P3AnalyzerWindow(self)

    def go_to_reader_window(self):
        self.hide()
        self.p_reader.show()

    def go_to_analyzer_window(self):
        self.hide()
        self.p_analyzer.show()
