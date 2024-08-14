from myqt.default.paragraph_window import *
from myqt.p5.p5_reader_window import P5ReaderWindow
from myqt.p5.p5_analyzer_window import P5AnalyzerWindow


class P5Window(PWindow):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        # Define available windows to switch
        self.p_reader = P5ReaderWindow(self)
        self.p_analyzer = P5AnalyzerWindow(self)

    def go_to_reader_window(self):
        self.hide()
        self.p_reader.show()

    def go_to_analyzer_window(self):
        self.hide()
        self.p_analyzer.show()
