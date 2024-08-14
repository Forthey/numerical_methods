from myqt.default.analyzer_window import *

from analyze.p5 import analyze


class P5AnalyzerWindow(AnalyzerWindow):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)
        self.label_left.setText("x1:")
        self.label_right.setText("x2:")

    def analyze_results(self):
        x1 = float(self.input_left.text())
        x2 = float(self.input_right.text())

        if self.check_1.isChecked():
            analyze(1, x1, x2)
        if self.check_2.isChecked():
            analyze(2, x1, x2)

        alert = QMessageBox(self)
        alert.setText("Saved in 'plots' folder")
        alert.exec()

        self.go_back_to_parent_window()
