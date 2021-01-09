//
// Created by filipz on 1/4/21.
//

#include "BusinessTable.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>

BusinessTable::BusinessTable(int x, int y, int w, int h, const char *l, BusinessTableModel *model) :
Fl_Table_Row(x, y, w, h, l), model(model) {

    rows(model->getNumberOfRows());
    row_header(1);
    row_height_all(20);
    row_resize(0);
    type(SELECT_SINGLE);


    cols(model->getNumberOfColumns());
    col_header(1);
    // col_width_all(80);
    col_resize(1);
    end();
}

void BusinessTable::draw_cell(TableContext context, int row, int column, int x , int y, int w, int h) {
    switch (context)
    {
        case CONTEXT_COL_HEADER:
        {
            fl_push_clip(x, y, w, h);
            {
                fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, col_header_color());
                fl_color(FL_BLACK);
                fl_draw(model->getColumnHeader(column).c_str(), x, y, w, h, FL_ALIGN_CENTER);
            }
            fl_pop_clip();
            return;
        }
        case CONTEXT_ROW_HEADER:
        {
            fl_push_clip(x, y, w, h);
            {
                fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, col_header_color());
                fl_color(FL_BLACK);
                fl_draw(model->getRowHeader(row).c_str(), x - 2, y, w, h, FL_ALIGN_RIGHT);
            }
            fl_pop_clip();
            return;
        }
        case CONTEXT_CELL:
        {
            fl_push_clip(x, y, w, h);
            {
                fl_color(row_selected(row) ? FL_SELECTION_COLOR : FL_WHITE);
                fl_rectf(x, y, w, h);
                fl_color(row_selected(row) ? FL_WHITE : FL_BLACK);
                fl_draw(model->getCellValue(row, column).c_str(), x + 2, y, w, h, FL_ALIGN_LEFT);
                fl_color(color());
                fl_rect(x, y, w, h);
            }
            fl_pop_clip();
            return;
        }
        case CONTEXT_STARTPAGE:
        case CONTEXT_TABLE:
        case CONTEXT_ENDPAGE:
        case CONTEXT_RC_RESIZE:
        case CONTEXT_NONE:
            return;
    }
}

#include <iostream>

void BusinessTable::updateRows() {
    cout << "UPDATE_ROWS" << endl;
    rows(this->model->getNumberOfRows());
}

    BusinessTableModel* BusinessTable::getModel() const {
    return model;
}