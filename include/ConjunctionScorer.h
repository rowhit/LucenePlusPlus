/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2010 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Scorer.h"

namespace Lucene
{
	/// Scorer for conjunctions, sets of queries, all of which are required.
	class LPPAPI ConjunctionScorer : public Scorer
	{
	public:
		ConjunctionScorer(SimilarityPtr similarity, Collection<ScorerPtr> scorers);
		virtual ~ConjunctionScorer();
	
		LUCENE_CLASS(ConjunctionScorer);
	
	protected:
		Collection<ScorerPtr> scorers;
		double coord;
		int32_t lastDoc;
	
	public:
		virtual int32_t advance(int32_t target);
		virtual int32_t docID();
		virtual int32_t nextDoc();
		virtual double score();
	
	protected:
		int32_t doNext();
	};
}