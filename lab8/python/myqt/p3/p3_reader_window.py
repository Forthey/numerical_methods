from myqt.default.reader_window import *

from analyze.utility import write


class P3ReaderWindow(ReaderWindow):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        self.input_exp_cnt.setText("3")
        self.input_step.setText("2")

    def read_info(self):
        left = float(self.input_left.text())
        right = float(self.input_right.text())
        exp_cnt = int(self.input_exp_cnt.text())
        step = int(self.input_step.text())
        grid_id = int(self.combo_grid.currentIndex())

        if self.check_1.isChecked():
            write(1, 3, exp_cnt, 6, step, left, right, grid_id)
        if self.check_2.isChecked():
            write(2, 3, exp_cnt, 6, step, left, right, grid_id)

        alert = QMessageBox(self)
        alert.setText("Saved in 'data' folder")
        alert.exec()

        self.go_back_to_parent_window()
