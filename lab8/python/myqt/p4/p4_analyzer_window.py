from myqt.default.analyzer_window import *

from analyze.p4 import analyze


class P4AnalyzerWindow(AnalyzerWindow):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

    def analyze_results(self):
        left = float(self.input_left.text())
        right = float(self.input_right.text())
        if self.check_1.isChecked():
            analyze(1, left, right)
        if self.check_2.isChecked():
            analyze(2, left, right)

        alert = QMessageBox(self)
        alert.setText("Saved in 'plots' folder")
        alert.exec()

        self.go_back_to_parent_window()
